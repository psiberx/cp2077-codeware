"""Parse the active struct definitions of the RED4ext SDK headers (generated and hand-written)."""
import os, re

def mask_comments(text):
    out = []
    i = 0
    n = len(text)
    res = list(text)
    # block comments
    for m in re.finditer(r'/\*.*?\*/', text, re.S):
        for k in range(m.start(), m.end()):
            if res[k] != '\n':
                res[k] = ' '
    t = ''.join(res)
    res = list(t)
    for m in re.finditer(r'//[^\n]*', t):
        for k in range(m.start(), m.end()):
            res[k] = ' '
    return ''.join(res)

NS_RE = re.compile(r'\bnamespace\s+([\w:]+)\s*\{|\{|\}')
STRUCT_RE = re.compile(r'\bstruct\s+((?:__declspec\(align\((?:0x)?[0-9A-Fa-f]+\)\)\s+)?)(\w+)\s*(?::\s*([^{;]+?))?\s*\{')

def parse_file(path):
    text = open(path, errors='replace').read()
    masked = mask_comments(text)
    # namespace tracking: list of (pos, kind) events
    events = [(m.start(), m.group(0), m.group(1)) for m in NS_RE.finditer(masked)]
    structs = []
    stack = []   # entries: ('ns', name) or ('blk', None)
    ei = 0
    for sm in STRUCT_RE.finditer(masked):
        sp = sm.start()
        while ei < len(events) and events[ei][0] < sm.end() - 1:   # events before the struct's opening brace
            pos, tok, name = events[ei]
            if tok.startswith('namespace'):
                stack.append(('ns', name))
            elif tok == '{':
                stack.append(('blk', None))
            else:
                if stack: stack.pop()
            ei += 1
        # the struct's own '{' is at sm.end()-1; make sure we consumed up to before it
        if any(k == 'blk' for k, _ in stack):
            continue     # nested in another block (struct inside struct/function): skip
        ns = [n for k, n in stack if k == 'ns']
        # brace match for the body
        depth = 0
        j = sm.end() - 1
        while j < len(masked):
            c = masked[j]
            if c == '{': depth += 1
            elif c == '}':
                depth -= 1
                if depth == 0: break
            j += 1
        body_start = sm.end()
        body_end = j
        structs.append(dict(path=path, ns=ns, align=sm.group(1).strip(), name=sm.group(2), bases=(sm.group(3) or '').strip(),
                            start=sp, brace=sm.end()-1, body_start=body_start, body_end=body_end,
                            text=text, masked=masked))
    return structs

MEM_RE = re.compile(r'^\s*([\w:<>,\s\*&]+?)\s+(\w+)((?:\s*\[[^\]]+\])*)\s*;\s*$')
SKIP_PREFIX = ('static', 'virtual', 'using', 'typedef', 'friend', 'template', 'enum', 'struct', 'union', 'return', 'public', 'private', 'protected', 'constexpr', 'inline', 'explicit')

def members(st):
    """Data members of a parsed struct: list of dict(type, name, array, line_index, is_pad). line numbers are absolute (0-based) in st['text']."""
    text, masked = st['text'], st['masked']
    body = masked[st['body_start']:st['body_end']]
    base_line = masked.count('\n', 0, st['body_start'])
    res = []
    depth = 0
    for k, line in enumerate(body.split('\n')):
        s = line.strip()
        if k == 0:
            s = line.strip()
        if not s or s.startswith('#'):
            continue
        if '(' in s or ')' in s or ':' in s.replace('::', '') or '{' in s or '}' in s or '=' in s:
            res.append(dict(kind='other', line=base_line + k, text=s))
            continue
        if s.startswith(SKIP_PREFIX):
            res.append(dict(kind='other', line=base_line + k, text=s))
            continue
        m = MEM_RE.match(line)
        if not m:
            res.append(dict(kind='other', line=base_line + k, text=s))
            continue
        typ, name, arr = m.group(1).strip(), m.group(2), m.group(3).strip()
        is_pad = typ == 'uint8_t' and name.startswith('unk') and arr
        res.append(dict(kind='pad' if is_pad else 'member', type=typ, name=name, array=arr, line=base_line + k))
    return res

def qualified(st):
    return '::'.join(st['ns'] + [st['name']])

def reflect_name(st):
    m = re.search(r'static constexpr const char\* NAME = "([^"]+)"', st['text'][st['body_start']:st['body_end']])
    return m.group(1) if m else None

def walk(sdk):
    for root, _, files in os.walk(sdk):
        for f in sorted(files):
            if f.endswith('.hpp'):
                yield os.path.join(root, f)

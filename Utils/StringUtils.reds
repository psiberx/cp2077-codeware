module Codeware.StringUtils

public func SplitWords(str: String, splitChars: array<String>) -> array<String> {
	let parts: array<String>;

	let startIndex = 0;
	let index = StrFindAny(str, splitChars, startIndex);

	while (true) {
		let index = StrFindAny(str, splitChars, startIndex);

		if (index == -1) {
			ArrayPush(parts, StrMid(str, startIndex, StrLen(str) - 1));
			return parts;
		}

		let word = StrMid(str, startIndex, index - startIndex);
		let nextChar = StrMid(str, index, 1);

		if (UnicodeStringEqual(nextChar, " ")) {
			ArrayPush(parts, word);
			ArrayPush(parts, nextChar);
		} else {
			ArrayPush(parts, word + nextChar);
		}

		startIndex = index + 1;
	}
}

public func StrTrimStart(const str: String) -> String {
	while StrBeginsWith(str, " ") {
		str = StrMid(str, 1, StrLen(str) - 1);
	}
	return str;
}

private func StrFindAny(const str: String, matches: array<String>, startIndex: Int32) -> Int32 {
	let searchString = StrMid(str, startIndex, StrLen(str) - 1);
	let firstMatchedIndex = -1;
	let i = 0;
	while (i < ArraySize(matches)) {
		let match = StrFindFirst(searchString, matches[i]);
		if (firstMatchedIndex == -1 || (firstMatchedIndex != -1 && match < firstMatchedIndex && match != -1)) {
			firstMatchedIndex = match;
		}
		i += 1;
	}

	if (firstMatchedIndex == -1) {
		return -1;
	} else {
		return startIndex + firstMatchedIndex;
	}
}
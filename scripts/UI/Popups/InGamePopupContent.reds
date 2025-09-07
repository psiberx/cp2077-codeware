// -----------------------------------------------------------------------------
// Codeware.UI.InGamePopupContent
// -----------------------------------------------------------------------------

module Codeware.UI

public class InGamePopupContent extends inkCustomController {
    protected let m_content: wref<inkFlex>;

    protected cb func OnCreate() {
        let content: ref<inkFlex> = new inkFlex();
        content.SetName(n"content");
        content.SetMargin(inkMargin(76.0, 135.0, 0.0, 118.0));
        content.SetAnchor(inkEAnchor.Fill);

        this.m_content = content;

        this.SetRootWidget(content);
    }

    protected cb func OnReparent(parent: ref<inkCompoundWidget>) ->  Void {
        let contentMargin: inkMargin = this.GetRootWidget().GetMargin();

        let contentSize: Vector2 = parent.GetSize();
        contentSize.X -= contentMargin.left + contentMargin.right;
        contentSize.Y -= contentMargin.top + contentMargin.bottom;

        this.m_content.SetSize(contentSize);
    }

    public func GetSize() -> Vector2 {
        return this.m_content.GetSize();
    }

    public static func Create() -> ref<InGamePopupContent> {
        let self: ref<InGamePopupContent> = new InGamePopupContent();
        self.CreateInstance();

        return self;
    }
}

module Style = ReactDOMRe.Style;

type mode =
  | Primary
  | Secondary
  | Danger;

let component = ReasonReact.statelessComponent("Button");

let baseStyle = (main, dark) =>
  Style.make(
    ~cursor="pointer",
    ~backgroundColor=main,
    ~color=dark,
    ~borderColor=dark,
    (),
  );

let style =
  fun
  | Primary => baseStyle("#6AFF90", "#0d481c")
  | Secondary => baseStyle("#509bf5", "#072d5a")
  | Danger => baseStyle("#eb1e32", "#5f030c");

let make = (~node, ~mode, ~onClick, children) => {
  ...component,
  render: _self =>
    <button style={Yoga.project(node, style(mode))} onClick>
      {ReasonReact.array(children)}
    </button>,
};

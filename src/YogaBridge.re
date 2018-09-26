let project = (node, style) => {
  let layout = Yoga.Node.computedLayout(node);
  let top = string_of_int(layout.top) ++ "px";
  let left = string_of_int(layout.left) ++ "px";
  let width = string_of_int(layout.width) ++ "px";
  let height = string_of_int(layout.height) ++ "px";
  ReactDOMRe.Style.combine(
    style,
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~top={j|$top|j},
      ~left={j|$left|j},
      ~width={j|$width|j},
      ~height={j|$height|j},
      (),
    ),
  );
};

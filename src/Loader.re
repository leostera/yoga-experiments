module Style = ReactDOMRe.Style;

/**
The main state of the Loader component.
*/
type phase =
  | Loading
  | Error
  | Ok;

type state = {
  node: Yoga.Node.t,
  text_node: Yoga.Node.t,
};

type action =
  | Continue
  | Fail
  | Reset;

let component = ReasonReact.reducerComponent("Loader");

let fullScreenNode = () =>
  Yoga.Node.create({
    width: Window.width,
    height: Window.height,
    justify_content: Center,
    flex_direction: Column,
    align_items: Center,
  });

let textNode = (node, text) =>
  <div style={Yoga.project(node, Style.make(~color="#eaeaea", ()))}>
    {ReasonReact.string(text)}
  </div>;

let make = (~width, ~height, ~phase, children) => {
  ...component,
  /***
    For the initial state we will always be loading.
   */
  initialState: () => {
    let text_node =
      Yoga.Node.create({
        /* TODO(@ostera): this should 100% be known from the text+typeface */
        width: 70,
        height: 20,
        justify_content: Center,
        flex_direction: Column,
        align_items: Center,
      });
    {
      text_node,
      node:
        fullScreenNode()
        |> Yoga.Node.insertChild(text_node, 0)
        |> Yoga.Node.calculateLayout({
             width,
             height,
             direction: Left_to_right,
           }),
    };
  },
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: self =>
    <div
      style={
        Yoga.project(
          self.state.node,
          Style.make(~backgroundColor="#403E48", ()),
        )
      }>
      {
        switch (phase) {
        | Ok => ReasonReact.array(children)
        | Error => textNode(self.state.text_node, "ERROR")
        | Loading => textNode(self.state.text_node, "Loading...")
        }
      }
    </div>,
};

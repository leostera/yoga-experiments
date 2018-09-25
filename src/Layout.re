module Style = ReactDOMRe.Style;

type button = {
  node: Yoga.Node.t,
  text: string,
};
let button = text => {
  text,
  node:
    Yoga.Node.create({
      width: 100,
      height: 100,
      justify_content: Space_between,
      flex_direction: Row,
      align_items: Center,
    }),
};

type buttons = {
  reset: button,
  continue: button,
  fail: button,
};

type nav = {
  node: Yoga.Node.t,
  buttons,
};

type state = {
  root: Yoga.Node.t,
  nav,
  phase: Loader.phase,
};

type action =
  | Continue
  | Fail
  | Reset;

let component = ReasonReact.reducerComponent("Layout");

let make = (~width, ~height, children) => {
  ...component,
  /***
    For the initial state we will always be loading.
   */
  initialState: () => {
    let buttons = {
      reset: button("Reset"),
      continue: button("Continue"),
      fail: button("Error"),
    };
    let nav = {
      node:
        Yoga.Node.create({
          width,
          height: 100,
          justify_content: Space_evenly,
          flex_direction: Row,
          align_items: Center,
        })
        |> Yoga.Node.insertChild(buttons.reset.node, 0)
        |> Yoga.Node.insertChild(buttons.continue.node, 1)
        |> Yoga.Node.insertChild(buttons.fail.node, 2),
      buttons,
    };
    {
      nav,
      root:
        Yoga.Node.create({
          width,
          height,
          justify_content: Flex_start,
          flex_direction: Column,
          align_items: Flex_start,
        })
        |> Yoga.Node.insertChild(nav.node, 0)
        |> Yoga.Node.calculateLayout({
             width: Window.width,
             height: Window.height,
             direction: Left_to_right,
           }),
      phase: Loader.Loading,
    };
  },
  /***
    Here we define how to transition between states using actions.
   */
  reducer: (action, state) =>
    switch (action) {
    | Continue => ReasonReact.Update({...state, phase: Ok})
    | Fail => ReasonReact.Update({...state, phase: Error})
    | Reset => ReasonReact.Update({...state, phase: Loading})
    },
  render: self =>
    <div style={Yoga.project(self.state.root, Style.make())}>
      <nav
        style={
          Yoga.project(self.state.nav.node, Style.make(~zIndex="1000", ()))
        }>
        <Button
          node={self.state.nav.buttons.reset.node}
          mode=Secondary
          onClick={_event => self.send(Reset)}>
          {ReasonReact.string(self.state.nav.buttons.reset.text)}
        </Button>
        <Button
          node={self.state.nav.buttons.continue.node}
          mode=Primary
          onClick={_event => self.send(Continue)}>
          {ReasonReact.string(self.state.nav.buttons.continue.text)}
        </Button>
        <Button
          node={self.state.nav.buttons.fail.node}
          mode=Danger
          onClick={_event => self.send(Fail)}>
          {ReasonReact.string(self.state.nav.buttons.fail.text)}
        </Button>
      </nav>
      <Loader width height phase={self.state.phase}>
        <div> {ReasonReact.string("Yo! This is some stuff")} </div>
      </Loader>
    </div>,
};

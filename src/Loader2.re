module type Base = {
  /** The component to wrap with a loading state */
  let make: 'a => ReasonReact.reactElement;
};

module Wrap = (Comp: Base) => {
  /**
  The main state of the Loader component.
  */
  type state =
    | Loading
    | Error
    | Ok;

  type action =
    | Continue
    | Fail
    | Begin;

  let component = ReasonReact.reducerComponent("Loader");

  let make = _children => {
    ...component,
    /***
      For the initial state we will always be loading.
     */
    initialState: () => Loading,
    /***
      Here we define how to transition between states using actions.
     */
    reducer: (action, _state) =>
      switch (action) {
      | Continue => ReasonReact.Update(Ok)
      | Fail => ReasonReact.Update(Error)
      | Begin => ReasonReact.Update(Loading)
      },
    render: self =>
      <div>
        <button onClick={_event => self.send(Begin)}>
          {ReasonReact.string("Begin!")}
        </button>
        <button onClick={_event => self.send(Continue)}>
          {ReasonReact.string("Continue!")}
        </button>
        <button onClick={_event => self.send(Fail)}>
          {ReasonReact.string("Fail!")}
        </button>
        {
          switch (self.state) {
          | Ok => Comp.make()
          | Error => ReasonReact.string("ERROR")
          | Loading => ReasonReact.string("Loading...")
          }
        }
      </div>,
  };
};

type action =
  | UpdateText(string);

type state = {composerValue: string};

let valueFromEvent = evt : string => ReactDOMRe.domElementToObj(
                                       ReactEventRe.Form.target(evt)
                                     )##value;

let component = ReasonReact.reducerComponent("Composer");

let make = _children => {
  ...component,
  initialState: () => {composerValue: ""},
  reducer: (action, _state) =>
    switch action {
    | UpdateText(text) => ReasonReact.Update({composerValue: text})
    },
  render: ({state, reduce}) =>
    <div>
      <p>
        (ReasonReact.stringToElement("Inputed Text:" ++ state.composerValue))
      </p>
      <textarea
        value=state.composerValue
        onChange=(reduce(event => UpdateText(valueFromEvent(event))))
      />
    </div>
};

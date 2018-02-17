[%bs.raw {|require('./composer.css')|}];

type action =
  | UpdateText(string);

type state = {
  composerValue: string,
  mention: option(string)
};

let component = ReasonReact.reducerComponent("Composer");

let make = _children => {
  ...component,
  initialState: () => {composerValue: "", mention: None},
  reducer: (action, _state) =>
    switch action {
    | UpdateText(text) =>
      let mention =
        Js.String.match([%re "/\\B@[a-zA-Z0-9_]{1,15}\\b/g"], text)
        |> (
          fun
          | Some(arrayOfMentions) =>
            Some(arrayOfMentions[Array.length(arrayOfMentions) - 1])
          | None => None
        );
      ReasonReact.Update({composerValue: text, mention});
    },
  render: ({state: {composerValue, mention}, send}) =>
    <div>
      <p className="Composer-title">
        (
          ReasonReact.stringToElement(
            "Current Mention: "
            ++ (
              switch mention {
              | None => "None"
              | Some(mentionText) => mentionText
              }
            )
          )
        )
      </p>
      <textarea
        className="Composer-textarea"
        placeholder="What's happening?"
        value=composerValue
        onChange=(
          event =>
            send(
              UpdateText(
                ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
              )
            )
        )
      />
    </div>
};

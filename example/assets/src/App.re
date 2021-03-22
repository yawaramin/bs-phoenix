// Entry point

%raw
{|require('phoenix_html'),require('../css/app.scss')|};
module Document = Webapi.Dom.Document;
module Element = Webapi.Dom.Element;
module HtmlElement = Webapi.Dom.HtmlElement;
[@set] external setValue: (Element.t, string) => unit = "value";
external eventToKeyboardEvent: Dom.event => Webapi.Dom.KeyboardEvent.t =
  "%identity";
[@bs.val]
external json_stringify: ('a, Js.Nullable.t(unit), int) => string =
  "JSON.stringify";
let stringify = str => json_stringify(str, Js.Nullable.null, 2);

let%private params = {
  "userToken": "",
  "logger": (kind, msg, data) =>
    Js.log2(kind ++ ": " ++ msg ++ ", ", stringify(data)),
};
open Phoenix;
let socket = Socket.make("/socket",params);
socket |> Socket.connect();
let channel = Socket.channel("room:lobby", socket);

let document = Webapi.Dom.document;
let option_msgList = Document.getElementById("msg-list", document);
let name = Document.getElementById("name", document);
let msg = Document.getElementById("msg", document);
let getValue = (element: option(Element.t)): option(string) =>
  element
  ->Belt.Option.map(_, Element.unsafeAsHtmlElement)
  ->Belt.Option.map(_, HtmlElement.value);
let getList = () =>
  switch (option_msgList) {
  | None => raise(Invalid_argument("getList failed"))
  | Some(el) => el
  };
let getMsg = () =>
  switch (msg) {
  | None => raise(Invalid_argument("getList failed"))
  | Some(el) => el
  };

let updateMsgList = (name, message): unit => {
  let msgList = getList();
  let li = document |> Document.createElement("li");
  let newMessage = "<b>" ++ name ++ "</b>: " ++ message;
  Element.setInnerHTML(li, newMessage);
  msgList |> Element.appendChild(li);
  // reset the message input field for next message.
  setValue(getMsg(), "");
  ();
};

channel
|> Channel.on("shout", payload => {
     let name =
       if (payload##name !== "") {
         payload##name;
       } else {
         "guest";
       };

     updateMsgList(name, payload##message);
   });

channel |> Channel.join(_) |> ignore;

let eventHandler = event => {
  let event = event->eventToKeyboardEvent;
  let keyCode = Webapi.Dom.KeyboardEvent.key(event);
  // get value of "name" of person sending the message
  // don't sent empty name.
  let _name = getValue(name);
  let name =
    if (_name !== Some("")) {
      _name;
    } else {
      Some("guest");
    };
  // check if `Enter` is the key code
  let keyCodeIsEnter = keyCode == "Enter";
  // get message text (value) from msg input field
  let someMessage = getValue(msg) !== Some("");
  // don't sent empty msg.
  if (keyCodeIsEnter && someMessage) {
    // send the message to the server on "shout" channel
    channel
    |> Channel.push("shout", {"name": name, "message": getValue(msg)}, _)
    |> Push.receive("ok", Js.log2("Created message"))
    |> Push.receive("error", Js.log2("Create failed"))
    |> Push.receive("timeout", _ => Js.log("Network issue"))
    |> ignore;
  };
};

switch (msg) {
| Some(elem) =>
  Webapi.Dom.EventTarget.addEventListener(
    "keypress",
    eventHandler,
    Webapi.Dom.Element.asEventTarget(elem),
  )
| None => ()
};

type event = Push.event;
type timeoutMs = Push.timeoutMs;

module rec Channel: {
  type t;

  [@bs.send.pipe: t] external canPush: unit => bool = "canPush";

  [@bs.send.pipe: t]
  external join: (~timeoutMs: timeoutMs=?) => Push.t = "join";

  [@bs.send.pipe: t]
  external leave: (~timeoutMs: timeoutMs=?) => Push.t = "push";

  [@bs.new] [@bs.module "phoenix"]
  external make: (string, Js.t('params), Socket.t) => t = "Channel";

  [@bs.send.pipe: t] external off: event => unit = "off";

  [@bs.send.pipe: t] external on: (event, 'reason => 'a) => unit = "on";

  [@bs.send.pipe: t] external onClose: ('reason => 'a) => unit = "onClose";

  [@bs.send.pipe: t] external onError: ('reason => 'a) => unit = "onError";

  [@bs.send.pipe: t]
  external push: (event, Js.t('payload), ~timeoutMs: timeoutMs=?) => Push.t =
    "push";

  [@bs.send] external rejoinUntilConnected: t => _ = "rejoinUntilConnected";
} = Channel

and Socket: {
  type t;

  [@bs.send.pipe: t]
  external channel: (string, ~chanParams: Js.t('params)=?) => Channel.t =
    "channel";
  // passing params to connect is deprecated. Instead pass :params to the Socket constructor
  // [@bs.send.pipe: t] external connect: Js.t('params) => unit = "connect";

  [@bs.send.pipe: t] external connect: unit => unit = "connect";

  [@bs.send] external connectionState: t => string = "channel";

  [@bs.send.pipe: t]
  external disconnect: (unit => 'a, 'code, string) => 'a = "connectionState";

  [@bs.send] external endPointURL: t => string = "endPointURL";

  [@bs.send] external isConnected: t => bool = "isConnected";

  [@bs.new] [@bs.module "phoenix"]
  external make: (string, Js.t('opts)) => t = "Socket";

  [@bs.send.pipe: t] external onClose: (event => 'a) => unit = "onClose";

  [@bs.send] external onConnOpen: t => unit = "onConnOpen";

  [@bs.send.pipe: t] external onConnClose: event => unit = "onConnClose";

  [@bs.send.pipe: t] external onConnError: event => unit = "onConnError";

  [@bs.send.pipe: t] external onError: (event => 'a) => unit = "onError";

  [@bs.send.pipe: t] external onMessage: (event => 'a) => unit = "onMessage";

  [@bs.send.pipe: t] external onOpen: (event => 'a) => unit = "onOpen";

  [@bs.send] external protocol: t => string = "protocol";

  [@bs.send.pipe: t] external remove: Channel.t => unit = "remove";

  [@bs.send] external triggerChanError: t => unit = "triggerChanError";
} = Socket;

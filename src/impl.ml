type event = Push.event
type timeoutMs = Push.timeoutMs

module rec Channel : sig
  type t

  external canPush : unit -> bool = "" [@@bs.send.pipe: t]
  external join : ?timeoutMs:timeoutMs -> Push.t = "" [@@bs.send.pipe: t]
  external leave : ?timeoutMs:timeoutMs -> Push.t = "" [@@bs.send.pipe: t]
  external make : string -> 'params Js.t -> Socket.t -> t = "Channel" [@@bs.new] [@@bs.module "phoenix"]
  external off : event -> unit = "" [@@bs.send.pipe: t]
  external on : event -> ('reason -> 'a) -> unit = "" [@@bs.send.pipe: t]
  external onClose : ('reason -> 'a) -> unit = "" [@@bs.send.pipe: t]
  external onError : ('reason -> 'a) -> unit = "" [@@bs.send.pipe: t]
  external push : event -> 'payload Js.t -> ?timeoutMs:timeoutMs -> Push.t = "" [@@bs.send.pipe: t]
  external rejoinUntilConnected : t -> _ = "" [@@bs.send]
end = Channel

and Socket : sig
  type t

  external channel : string -> ?chanParams:'params Js.t -> Channel.t = "" [@@bs.send.pipe: t]
  external connect : 'params Js.t -> unit = "" [@@bs.send.pipe: t]
  external connectionState : t -> string = "" [@@bs.send]
  external disconnect : (unit -> 'a) -> 'code -> string -> 'a = "" [@@bs.send.pipe: t]
  external endPointURL : t -> string = "" [@@bs.send]
  external isConnected : t -> bool = "" [@@bs.send]
  external make : string -> 'opts Js.t -> t = "Socket" [@@bs.new] [@@bs.module "phoenix"]
  external onClose : (event -> 'a) -> unit = "" [@@bs.send.pipe: t]
  external onConnOpen : t -> unit = "" [@@bs.send]
  external onConnClose : event -> unit = "" [@@bs.send.pipe: t]
  external onConnError : event -> unit = "" [@@bs.send.pipe: t]
  external onError : (event -> 'a) -> unit = "" [@@bs.send.pipe: t]
  external onMessage : (event -> 'a) -> unit = "" [@@bs.send.pipe: t]
  external onOpen : (event -> 'a) -> unit = "" [@@bs.send.pipe: t]
  external protocol : t -> string = "" [@@bs.send]
  external remove : Channel.t -> unit = "" [@@bs.send.pipe: t]
  external triggerChanError : t -> unit = "" [@@bs.send]
end = Socket

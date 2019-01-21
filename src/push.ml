type event = string
type t
type timeoutMs = float

external receive : event -> ('payload Js.t -> unit) -> t = "" [@@bs.send.pipe: t]
external resend : timeoutMs -> _ = "" [@@bs.send.pipe: t]
external send : t -> _ = "" [@@bs.send]

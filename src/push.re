type event = string;
type t;
type timeoutMs = float;

[@bs.send.pipe: t]
external receive: (event, Js.t('payload) => unit) => t = "receive";

[@bs.send.pipe: t] external resend: timeoutMs => _ = "resend";

[@bs.send] external send: t => _ = "send";

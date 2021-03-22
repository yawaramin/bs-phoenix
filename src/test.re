[@bs.val]
external json_stringify: ('a, Js.Nullable.t(unit), int) => string =
  "JSON.stringify";
let stringify = str => json_stringify(str, Js.Nullable.null, 2);
let () = {
  let params = {
    "userToken": "",
    "logger": (kind, msg, data) =>
      Js.log2(kind ++ ": " ++ msg ++ ", ", stringify(data)),
  };
  let socket = Socket.make("/socket", params);

  socket |> Socket.connect();
  let channel = Socket.channel("room:lobby", socket);

  Channel.on("shout", Js.log2("Got message"), channel);

  channel
  |> Channel.join(_)
  |> Push.receive("ok", Js.log2("Catching up"))
  |> Push.receive("error", payload =>
       Js.log2("Failed to join", payload##reason)
     )
  |> Push.receive("timeout", _ => Js.log("Network issue. Still waiting..."))
  |> ignore;

  channel
  |> Channel.push("shout", [%obj {body: "a"}], ~timeoutMs=10_000.0)
  |> Push.receive("ok", Js.log2("Created message"))
  |> Push.receive("error", Js.log2("Create failed"))
  |> Push.receive("timeout", _ => Js.log("Network issue"))
  |> ignore;
};

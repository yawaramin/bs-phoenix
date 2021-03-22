module type PresenceModule = {type nonrec t;};

module MakeModule = (Presence: PresenceModule) => {
  type nonrec t;

  type nonrec presence = {metas: array(Presence.t)};

  type nonrec presences = Js.Dict.t(presence);

  type nonrec diff = {
    joins: presences,
    leaves: presences,
  };

  type nonrec presenceCallback =
    (~id: string, ~currentPresence: presence, ~newPresence: presence) => unit;

  type nonrec presenceOpts = {
    state: string,
    diff: string,
  };

  [@module "phoenix"] [@new]
  external make: (Channel.t, option(presenceOpts)) => t = "Presence";

  [@module "phoenix"] [@scope "Presence"]
  external syncDiff:
    (
      ~currentState: presences,
      ~diff: diff,
      ~onJoin: presenceCallback=?,
      ~onLeave: presenceCallback=?,
      unit
    ) =>
    presences =
    "syncDiff";

  [@module "phoenix"] [@scope "Presence"]
  external syncState:
    (
      ~currentState: presences,
      ~newState: presences,
      ~onJoin: presenceCallback=?,
      ~onLeave: presenceCallback=?,
      unit
    ) =>
    presences =
    "syncState";

  [@set] external onLeave: (t, presenceCallback) => unit = "onLeave";
  [@set] external onJoin: (t, presenceCallback) => unit = "onJoin";

  let unwrap = presence => presence.metas->(Belt.Array.get(0));
};

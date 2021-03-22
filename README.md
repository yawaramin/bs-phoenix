# bs-phoenix - BuckleScript bindings for Phoenix.js

Phoenix.js is the JavaScript client for the Phoenix framework:
https://github.com/phoenixframework/phoenix/blob/v1.3/assets/js/phoenix.js

This binding aims to be as close as possible to idiomatic OCaml. There is
another existing binding, https://github.com/phoenix-china/bucklescript-phx ,
which is more feature-complete. The difference between this one and that is,
this one is very much a work in progress! Also, this one sticks more closely
with the `Module.function` idiom that's normal in OCaml.

For example, a JavaScript snippet from the Phoenix.js module:

```javascript
let socket = new Socket("/socket", {params: {userToken: "lobby"}})
```

translates to the corresponding OCaml in bs-phoenix:

```ocaml
open Phoenix

let socket = Socket.make "/socket" [%obj { params = { userToken = "lobby" } }]
```
```reason
let%private params = {
  "userToken": "",
  "logger": (kind, msg, data) =>
    Js.log2(kind ++ ": " ++ msg ++ ", ", data),
};
open Phoenix;
let socket = Socket.make("/socket",params);
```

## Use

Add the package to your npm project:

    $ npm install yawaramin/bs-phoenix

Add the BuckleScript dependency to your `bsconfig.json`:

    {
      ...,
      "bs-dependencies": [..., "bs-phoenix"]
    }

And see the `example/App.re` and `src/Test.re` files for examples of what the code should look
like.

## Running Example

  * Change into `example` directory with `cd example`
  * Install dependencies with `mix deps.get`
  * Create and migrate your database with `mix ecto.setup`
  * Install Node.js dependencies with `npm install` inside the `assets` directory
  * Compile Reason code `npm run watch`
  * Start Phoenix endpoint with `mix phx.server`

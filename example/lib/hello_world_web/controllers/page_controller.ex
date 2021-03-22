defmodule HelloWorldWeb.PageController do
  use HelloWorldWeb, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end
end

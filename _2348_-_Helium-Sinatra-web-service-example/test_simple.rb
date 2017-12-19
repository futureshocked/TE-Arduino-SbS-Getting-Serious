require './te_helium_demo'
require "rubygems"
require "sinatra"
require "rack/test"
require "test/unit"

class AppTest < Test::Unit::TestCase
  include Rack::Test::Methods

  def app
    HeliumApp.new
  end

  def test_home_get
    get "/"
    assert last_response.ok?
    assert_equal 'This is the Tech Explorations Helium Demo app', last_response.body

  end

  def test_home_post
    post '/helium_receive'
    assert last_response.ok?
    assert_equal 'ok', last_response.body
  end

end

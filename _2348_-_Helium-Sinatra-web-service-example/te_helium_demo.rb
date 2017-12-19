require 'sinatra/base'

class HeliumApp < Sinatra::Base

  get '/' do
    "This is the Tech Explorations Helium Demo app"
  end

  post '/helium_receive' do
    data = request.body.read # read the data from the request
    puts data # log data
    log = File.open("data.log","w")
    log.truncate(log.size)
    log.write(data)
    log.close
    "ok"
  end

  get '/helium_last_value' do
    log = File.open("data.log","r")
    data = log.read
    log.close
    puts "Send back #{data}"
    data
  end

  post '/helium_receive_json' do
    # grab json
    json      = JSON.parse(request.body.read)

    # create a new line
    data_new = "#{Time.new()} - data1:#{json['data1']},data2:#{json['data2']}\r\n"

    max_lines_to_store = 100

    # read the top lines only
    begin
      log = File.open("data_json.log","r")
      data_old = log.read
      log.close

      # a counter to help find the top lines
      line_counter=1
      #split the file by lines
      data_old.gsub!(/\r\n?/, "\n")
      data_old.each_line do |line|
        line_counter +=1
        data_new += line
        if line_counter == max_lines_to_store then
          break
        end
      end
    rescue Exception => e
      # do nothing in case its the first time we called this
    end

    log = File.open("data_json.log","w")
    log.truncate(log.size)
    log.write(data_new)
    log.close
    "ok"
  end

  get '/helium_get_json_all' do
    log = File.open("data_json.log","r")
    data_old = log.read
    log.close
    data_old
  end

  get '/helium_get_json_last10' do
    log = File.open("data_json.log","r")
    data_old = log.read
    log.close

    data_new = ""
    # Read only the top 10 lines
    line_counter=0
    data_old.gsub!(/\r\n?/, "\n")
    data_old.each_line do |line|
      line_counter +=1
      data_new += line
      if line_counter == 10 then
        break
      end
    end

    data_new
  end

  post '/helium_receive_csv' do
    # grab the csv
    csv      = request.body.read
    data = csv.split(",")

    # create a new line
    data_new = "#{Time.new()} - temperature:#{data[0]},humidity:#{data[1]},pressure:#{data[2]}, device ID:#{data[3]}\r\n"


    max_lines_to_store = 100

    # read the top lines only
    begin
      log = File.open("data_csv.log","r")
      data_old = log.read
      log.close

      # a counter to help find the top lines
      line_counter=1
      #split the file by lines
      data_old.gsub!(/\r\n?/, "\n")
      data_old.each_line do |line|
        line_counter +=1
        data_new += line
        if line_counter == max_lines_to_store then
          break
        end
      end
    rescue Exception => e
      # do nothing in case its the first time we called this
    end

    log = File.open("data_csv.log","w")
    log.truncate(log.size)
    log.write(data_new)
    log.close
    "ok"
  end

  get '/helium_get_csv_all' do
    log = File.open("data_csv.log","r")
    data_old = log.read
    log.close
    data_old
  end

  get '/helium_get_csv_last10' do
    log = File.open("data_csv.log","r")
    data_old = log.read
    log.close

    data_new = ""
    # Read only the top 10 lines
    line_counter=0
    data_old.gsub!(/\r\n?/, "\n")
    data_old.each_line do |line|
      line_counter +=1
      data_new += line
      if line_counter == 10 then
        break
      end
    end

    data_new
  end

end

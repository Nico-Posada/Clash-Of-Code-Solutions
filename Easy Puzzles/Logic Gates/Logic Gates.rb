toData = -> (binary, len) { binary.rjust(len, ?0).tr('01', '_-') }
toNData = -> (binary, len) { binary.rjust(len, ?0).tr('01', '-_') }

n = gets.to_i
m = gets.to_i

inputs = {}
n.times{ t, s = gets.split; inputs.store(t, s) }

m.times do
  output_name, type, input_name_1, input_name_2 = gets.split

  stream_a = inputs[input_name_1].tr('_-', '01').to_i(2)
  stream_b = inputs[input_name_2].tr('_-', '01').to_i(2)

  result = ''
  len = inputs[input_name_1].length

  case type
  when 'AND' then result = toData['%b' % (stream_a & stream_b), len]
  when 'OR' then result = toData['%b' % (stream_a | stream_b), len]
  when 'XOR' then result = toData['%b' % (stream_a ^ stream_b), len]
  when 'NAND' then result = toNData['%b' % (stream_a & stream_b), len]
  when 'NOR' then result = toNData['%b' % (stream_a | stream_b), len]
  when 'NXOR' then result = toNData['%b' % (stream_a ^ stream_b), len]
  end

  puts [output_name, result]*' '
end

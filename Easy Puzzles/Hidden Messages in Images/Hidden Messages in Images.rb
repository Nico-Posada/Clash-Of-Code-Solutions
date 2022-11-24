`sed 1d`.split.map{_1.to_i&1}.each_slice(8){$><<_1.join.to_i(2).chr}
# golfed

bLon,bLat=[gets,gets].map{_1.tr(?,,?.).to_f}
gets
a=$<.map{
  num,name,address,_,lon,lat=_1.split(?;)
  lon,lat=[lon,lat].map{|x|x.tr(?,,?.).to_f}
  [name, (((bLon-lon)*Math.cos((bLat+lat)/2.0))**2 + (bLat-lat)**2)**0.5 * 6371]
}
a.sort_by!{_2}
puts a[0][0]

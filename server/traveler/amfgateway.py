from pyamf.remoting.gateway.django import DjangoGateway
import iface


def echo(data):
    'simple echo function, for basic testing purpose'
    return data
   
   
#available services
services = {
    'traveler.echo'             : echo,
    'traveler.addCity'          : iface.addCity,
    'traveler.addRoute'         : iface.addRoute,
    'traveler.addCityToRoute'   : iface.addCityToRoute,
    'traveler.delCity'          : iface.delCity,
    'traveler.delRoute'         : iface.delRoute,
    'traveler.delCityFromRoute' : iface.delCityFromRoute,
    'traveler.getCities'        : iface.getCities,
    'traveler.getRoutes'        : iface.getRoutes,
    'traveler.getCitiesInRoute' : iface.getCitiesInRoute,
    'traveler.setHomeCity'      : iface.setHomeCity,
    'traveler.tspSolve'         : iface.tspSolve,
    'traveler.tspState'         : iface.tspState,
    'traveler.tspResult'        : iface.tspResult,
}
    

#open pyamf gateway, discard 'request' argument in service - handling functions    
gateway = DjangoGateway(services, expose_request = False)

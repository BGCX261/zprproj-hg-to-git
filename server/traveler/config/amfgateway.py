from pyamf.remoting.gateway.django import DjangoGateway

def echo(data):
    """simple echo function, for testing purposes"""
    return data
   
   
#available services
services = {
    'traveler.echo' : echo,
}
    

#open pyamf gateway, discard 'request' argument in service - handling functions    
gateway = DjangoGateway(services, expose_request = False)

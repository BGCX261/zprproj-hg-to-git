from django.conf.urls.defaults import *

urlpatterns = patterns('',
    #interface for traveler application, this matches request in form
    #'[server:port]/traveler/'
    (r'^$', 'server.traveler.amfgateway.gateway'),
    (r'^client/(?P<path>.*)$', 'django.views.static.serve',{'document_root': 'build/client'}),        
)

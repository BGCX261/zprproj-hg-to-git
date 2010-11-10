from django.conf.urls.defaults import *

urlpatterns = patterns('',
    #interface for traveler application, this matches request in form
    #'[server:port]/traveler/'
    (r'^$', 'traveler.amfgateway.gateway'),
)

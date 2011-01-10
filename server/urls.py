from django.conf.urls.defaults import *

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    #traveler app wil handle its requests on its own
    (r'^traveler', include('server.traveler.urls')),
)

*jwt secret required when using web module
-show error if not configured

> main.cpp
> > core
> > > app ->handle core app functions -> segfaults and etc -> should manage the running services in the future

> > web
> > > controller -> handle routes and process
> > > web-server -> handle user requests
> > > client -> process client request
> > > route
> > > router
> > > send -> send response to client request
> > > server ->handle http networking

> > networking
> > > url

> > helpers
> > > utils -> helper functions

add controller and route list with name=>route
search through routes and initiate controller then call handle request function with the name of the route found and other data
or just reuse the controller
-reusing might mix data and also thread safe thing.
-renew controller will handle mult threading issue and also memory foot print might be a bit small on this
-authentication is done once when client is first connected


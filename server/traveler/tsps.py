class Tsps:

    instance_ = None
    
    class Singleton:
        def __init__(self):
            self.tsps_ = dict()  
            
        def addTsp(self, tsp):
            self.tsps_[tsp.routeId] = tsp

        def getTsp(self, route_id):
            return self.tsps_.get(route_id)

        def delTsp(self, route_id):
            self.tsps_.pop(route_id, None)   

    def __init__(self):
        if not Tsps.instance_:
            Tsps.instance_ = Tsps.Singleton()
        self._EventHandler_instance = Tsps.instance_    
        
    def __getattr__(self, attr):
        """ Delegate access to implementation """
        return getattr(self.instance_, attr)

    def __setattr__(self, attr, value):
        """ Delegate access to implementation """
        return setattr(self.instance_, attr, value)


class Tsps:

    instance_ = None
    
    class Singleton:
        def __init__(self):
            self.tsps_ = dict()  
            
        def addTsp(self, tsp):
            self.tsps_[tsp.getId()] = tsp

        def getTsp(self, tsp_id):
            return self.tsps_.get(tsp_id)

        def delTsp(self, tsp_id):
            self.tsps_.pop(tsp_id, None)   

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


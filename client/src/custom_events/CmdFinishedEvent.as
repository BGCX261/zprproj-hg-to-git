package custom_events
{
	import flash.events.Event;

	public class CmdFinishedEvent extends Event
	{
		public static const TYPE :String = "command finished";
		
		public function CmdFinishedEvent(tsp_id : int)
		{
			super(TYPE);
			tspId_ = tsp_id;
		}
		
		public function getCmdId() : int
		{
			return tspId_;
		}
		
		private var tspId_ : int;
		
	}
}
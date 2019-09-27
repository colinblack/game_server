package com.sanguo.game.server.connectlogic.common.message.ProtoPush
{
	import laya.utils.Byte;
	public class PushOnceEveryDayReward
	{
		public static const PROTO:String = "ProtoPush.PushOnceEveryDayReward";
		public var package_root:*;
		public  var message:*;
		public function PushOnceEveryDayReward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushOnceEveryDayReward
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushOnceEveryDayReward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
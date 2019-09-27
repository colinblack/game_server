package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceBuyOrder
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceBuyOrder";
		public var package_root:*;
		public  var message:*;
		public function RequestAllianceRaceBuyOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceBuyOrder
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceBuyOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
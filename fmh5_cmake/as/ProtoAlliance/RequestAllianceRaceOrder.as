package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceOrder
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceOrder";
		public var package_root:*;
		public  var message:*;
		public function RequestAllianceRaceOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceOrder
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
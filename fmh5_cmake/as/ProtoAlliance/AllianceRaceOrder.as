package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceRaceOrder
	{
		public static const PROTO:String = "ProtoAlliance.AllianceRaceOrder";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var cdTs:int;
		public function AllianceRaceOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			cdTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.cdTs = this.cdTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceRaceOrder
		{
			id = undefined;
			cdTs = undefined;
			this.id = msgObj.id;
			this.cdTs = msgObj.cdTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceRaceOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceMemberDelOrder
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceMemberDelOrder";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public function RequestAllianceRaceMemberDelOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceMemberDelOrder
		{
			type = undefined;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceMemberDelOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
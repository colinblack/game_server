package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceMemberUpdateOrderBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceMemberUpdateOrderBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var orderType:int;
		public var count:int;
		public var target:int;
		public function RequestAllianceRaceMemberUpdateOrderBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			orderType = undefined;
			count = undefined;
			target = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.orderType = this.orderType;
			serializeObj.count = this.count;
			serializeObj.target = this.target;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceMemberUpdateOrderBC
		{
			aid = undefined;
			uid = undefined;
			orderType = undefined;
			count = undefined;
			target = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.orderType = msgObj.orderType;
			this.count = msgObj.count;
			this.target = msgObj.target;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceMemberUpdateOrderBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
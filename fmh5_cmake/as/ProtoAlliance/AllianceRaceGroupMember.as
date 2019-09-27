package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceRaceGroupMember
	{
		public static const PROTO:String = "ProtoAlliance.AllianceRaceGroupMember";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var point:int;
		public var count:int;
		public function AllianceRaceGroupMember(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			point = undefined;
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.point = this.point;
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceRaceGroupMember
		{
			aid = undefined;
			point = undefined;
			count = undefined;
			this.aid = msgObj.aid;
			this.point = msgObj.point;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceRaceGroupMember
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
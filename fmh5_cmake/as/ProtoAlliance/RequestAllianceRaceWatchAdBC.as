package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceWatchAdBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceWatchAdBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var point:int;
		public function RequestAllianceRaceWatchAdBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			point = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.point = this.point;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceWatchAdBC
		{
			aid = undefined;
			uid = undefined;
			point = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.point = msgObj.point;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceWatchAdBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
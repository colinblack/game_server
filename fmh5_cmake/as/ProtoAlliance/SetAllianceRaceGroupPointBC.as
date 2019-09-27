package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class SetAllianceRaceGroupPointBC
	{
		public static const PROTO:String = "ProtoAlliance.SetAllianceRaceGroupPointBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var point:int;
		public function SetAllianceRaceGroupPointBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			point = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.point = this.point;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetAllianceRaceGroupPointBC
		{
			aid = undefined;
			point = undefined;
			this.aid = msgObj.aid;
			this.point = msgObj.point;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetAllianceRaceGroupPointBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
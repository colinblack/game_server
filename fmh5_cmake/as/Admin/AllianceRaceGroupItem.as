package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class AllianceRaceGroupItem
	{
		public static const PROTO:String = "Admin.AllianceRaceGroupItem";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var count:int;
		public function AllianceRaceGroupItem(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceRaceGroupItem
		{
			aid = undefined;
			count = undefined;
			this.aid = msgObj.aid;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceRaceGroupItem
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
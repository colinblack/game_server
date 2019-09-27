package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestSeekDonationBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestSeekDonationBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var count:int;
		public var aid:int;
		public var propsid:int;
		public var cdtime:int;
		public var name:Byte;
		public var level:int;
		public function RequestSeekDonationBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			count = undefined;
			aid = undefined;
			propsid = undefined;
			cdtime = undefined;
			name = undefined;
			level = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.count = this.count;
			serializeObj.aid = this.aid;
			serializeObj.propsid = this.propsid;
			serializeObj.cdtime = this.cdtime;
			this.name.pos = 0;
			serializeObj.level = this.level;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestSeekDonationBC
		{
			uid = undefined;
			count = undefined;
			aid = undefined;
			propsid = undefined;
			cdtime = undefined;
			name = undefined;
			level = undefined;
			this.uid = msgObj.uid;
			this.count = msgObj.count;
			this.aid = msgObj.aid;
			this.propsid = msgObj.propsid;
			this.cdtime = msgObj.cdtime;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.level = msgObj.level;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestSeekDonationBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
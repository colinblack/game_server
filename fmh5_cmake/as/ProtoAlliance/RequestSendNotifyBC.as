package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestSendNotifyBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestSendNotifyBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var content:Byte;
		public var name:Byte;
		public function RequestSendNotifyBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			content = undefined;
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			this.content.pos = 0;
			this.name.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestSendNotifyBC
		{
			aid = undefined;
			uid = undefined;
			content = undefined;
			name = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.content = new Byte();
			this.content.writeArrayBuffer(msgObj.content);
			this.content.pos = 0;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestSendNotifyBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
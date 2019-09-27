package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestDelNotifyBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestDelNotifyBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var id:int;
		public function RequestDelNotifyBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestDelNotifyBC
		{
			aid = undefined;
			uid = undefined;
			id = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestDelNotifyBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
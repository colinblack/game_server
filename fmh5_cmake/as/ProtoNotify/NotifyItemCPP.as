package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import laya.utils.Byte;
	public class NotifyItemCPP
	{
		public static const PROTO:String = "ProtoNotify.NotifyItemCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var ts:int;
		public var content:Byte;
		public function NotifyItemCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			ts = undefined;
			content = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.ts = this.ts;
			this.content.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):NotifyItemCPP
		{
			id = undefined;
			ts = undefined;
			content = undefined;
			this.id = msgObj.id;
			this.ts = msgObj.ts;
			this.content = new Byte();
			this.content.writeArrayBuffer(msgObj.content);
			this.content.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NotifyItemCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
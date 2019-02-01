package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class RandomUserItemCPP
	{
		public static const PROTO:String = "ProtoNotify.RandomUserItemCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var type:int;
		public var uid:int;
		public var ts:int;
		public var content:Byte;
		public function RandomUserItemCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			type = undefined;
			uid = undefined;
			ts = undefined;
			content = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.type = this.type;
			serializeObj.uid = this.uid;
			serializeObj.ts = this.ts;
			this.content.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RandomUserItemCPP
		{
			id = undefined;
			type = undefined;
			uid = undefined;
			ts = undefined;
			content = undefined;
			this.id = msgObj.id;
			this.type = msgObj.type;
			this.uid = msgObj.uid;
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
		public function decode(buffer:*):RandomUserItemCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
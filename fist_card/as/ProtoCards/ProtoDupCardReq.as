package com.sanguo.game.server.connectlogic.common.message.ProtoCards
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoDupCardReq
	{
		public static const PROTO:String = "ProtoCards.ProtoDupCardReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function ProtoDupCardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoDupCardReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoDupCardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
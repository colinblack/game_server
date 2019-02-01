package com.sanguo.game.server.connectlogic.common.message.ProtoCards
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoUpdateCardReq
	{
		public static const PROTO:String = "ProtoCards.ProtoUpdateCardReq";
		public var package_root:*;
		public  var message:*;
		public var cardId:int;
		public var ud:int;
		public function ProtoUpdateCardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			cardId = undefined;
			ud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cardId = this.cardId;
			serializeObj.ud = this.ud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoUpdateCardReq
		{
			cardId = undefined;
			ud = undefined;
			this.cardId = msgObj.cardId;
			this.ud = msgObj.ud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoUpdateCardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
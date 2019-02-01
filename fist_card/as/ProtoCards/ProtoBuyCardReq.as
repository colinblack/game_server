package com.sanguo.game.server.connectlogic.common.message.ProtoCards
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBuyCardReq
	{
		public static const PROTO:String = "ProtoCards.ProtoBuyCardReq";
		public var package_root:*;
		public  var message:*;
		public var cardId:int;
		public function ProtoBuyCardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			cardId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cardId = this.cardId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBuyCardReq
		{
			cardId = undefined;
			this.cardId = msgObj.cardId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBuyCardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
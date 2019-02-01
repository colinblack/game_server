package com.sanguo.game.server.connectlogic.common.message.ProtoCards
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBuyCardResp
	{
		public static const PROTO:String = "ProtoCards.ProtoBuyCardResp";
		public var package_root:*;
		public  var message:*;
		public var item:CardsAllChangeCPP;
		public var commons:CommonItemsCPP;
		public function ProtoBuyCardResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			item = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.item = this.item.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBuyCardResp
		{
			item = undefined;
			commons = undefined;
			this.item = new CardsAllChangeCPP(package_root).unserialize(msgObj.item);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBuyCardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
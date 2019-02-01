package com.sanguo.game.server.connectlogic.common.message.ProtoCards
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoDupCardResp
	{
		public static const PROTO:String = "ProtoCards.ProtoDupCardResp";
		public var package_root:*;
		public  var message:*;
		public var item:CardsAllChangeCPP;
		public var commons:CommonItemsCPP;
		public function ProtoDupCardResp(root:*)
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
		public function unserialize(msgObj:*):ProtoDupCardResp
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
		public function decode(buffer:*):ProtoDupCardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
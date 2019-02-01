package com.sanguo.game.server.connectlogic.common.message.ProtoCards
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoDelCardResp
	{
		public static const PROTO:String = "ProtoCards.ProtoDelCardResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function ProtoDelCardResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoDelCardResp
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoDelCardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
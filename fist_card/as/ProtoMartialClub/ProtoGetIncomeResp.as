package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetIncomeResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetIncomeResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function ProtoGetIncomeResp(root:*)
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
		public function unserialize(msgObj:*):ProtoGetIncomeResp
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetIncomeResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
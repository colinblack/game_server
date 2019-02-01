package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetIncomeReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetIncomeReq";
		public var package_root:*;
		public  var message:*;
		public var martialGrade:int;
		public function ProtoGetIncomeReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			martialGrade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.martialGrade = this.martialGrade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetIncomeReq
		{
			martialGrade = undefined;
			this.martialGrade = msgObj.martialGrade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetIncomeReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
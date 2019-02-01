package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSBattleResultReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoCSBattleResultReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var myMartialGrade:int;
		public var commons:CommonItemsCPP;
		public var info:ProtoBattleDemo;
		public function ProtoCSBattleResultReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			myMartialGrade = undefined;
			commons = undefined;
			info = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.myMartialGrade = this.myMartialGrade;
			serializeObj.commons = this.commons.serialize();
			serializeObj.info = this.info.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSBattleResultReq
		{
			myUid = undefined;
			myMartialGrade = undefined;
			commons = undefined;
			info = undefined;
			this.myUid = msgObj.myUid;
			this.myMartialGrade = msgObj.myMartialGrade;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.info = new ProtoBattleDemo(package_root).unserialize(msgObj.info);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSBattleResultReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
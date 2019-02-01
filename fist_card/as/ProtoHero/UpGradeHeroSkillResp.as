package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UpGradeHeroSkillResp
	{
		public static const PROTO:String = "ProtoHero.UpGradeHeroSkillResp";
		public var package_root:*;
		public  var message:*;
		public var level:int;
		public var commons:CommonItemsCPP;
		public var battlePower:int;
		public function UpGradeHeroSkillResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			level = undefined;
			commons = undefined;
			battlePower = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.level = this.level;
			serializeObj.commons = this.commons.serialize();
			serializeObj.battlePower = this.battlePower;
			return serializeObj;
		}
		public function unserialize(msgObj:*):UpGradeHeroSkillResp
		{
			level = undefined;
			commons = undefined;
			battlePower = undefined;
			this.level = msgObj.level;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.battlePower = msgObj.battlePower;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UpGradeHeroSkillResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}
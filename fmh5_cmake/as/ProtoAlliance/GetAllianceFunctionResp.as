package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class GetAllianceFunctionResp
	{
		public static const PROTO:String = "ProtoAlliance.GetAllianceFunctionResp";
		public var package_root:*;
		public  var message:*;
		public var applyList:Vector.<AllianceApplyCPP>;
		public var donations:Vector.<AllianceDonationCPP>;
		public var aidlist:Vector.<AidInfoCPP>;
		public var invitelist:Vector.<AllianceInvitedCPP>;
		public function GetAllianceFunctionResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			applyList = new Vector.<AllianceApplyCPP>();
			donations = new Vector.<AllianceDonationCPP>();
			aidlist = new Vector.<AidInfoCPP>();
			invitelist = new Vector.<AllianceInvitedCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.applyList = [];
			for(var i:int = 0;i < this.applyList.length;i++)
			{
				serializeObj.applyList.push(this.applyList[i].serialize());
			}
			serializeObj.donations = [];
			for(var i:int = 0;i < this.donations.length;i++)
			{
				serializeObj.donations.push(this.donations[i].serialize());
			}
			serializeObj.aidlist = [];
			for(var i:int = 0;i < this.aidlist.length;i++)
			{
				serializeObj.aidlist.push(this.aidlist[i].serialize());
			}
			serializeObj.invitelist = [];
			for(var i:int = 0;i < this.invitelist.length;i++)
			{
				serializeObj.invitelist.push(this.invitelist[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetAllianceFunctionResp
		{
			applyList = new Vector.<AllianceApplyCPP>();
			donations = new Vector.<AllianceDonationCPP>();
			aidlist = new Vector.<AidInfoCPP>();
			invitelist = new Vector.<AllianceInvitedCPP>();
			for(var i:int = 0;i < msgObj.applyList.length;i++)
			{
				this.applyList.push(new AllianceApplyCPP(package_root).unserialize(msgObj.applyList[i]));
			}
			for(var i:int = 0;i < msgObj.donations.length;i++)
			{
				this.donations.push(new AllianceDonationCPP(package_root).unserialize(msgObj.donations[i]));
			}
			for(var i:int = 0;i < msgObj.aidlist.length;i++)
			{
				this.aidlist.push(new AidInfoCPP(package_root).unserialize(msgObj.aidlist[i]));
			}
			for(var i:int = 0;i < msgObj.invitelist.length;i++)
			{
				this.invitelist.push(new AllianceInvitedCPP(package_root).unserialize(msgObj.invitelist[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetAllianceFunctionResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}